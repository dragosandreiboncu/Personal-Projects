#include "skel.h"
uint16_t ip_checksum(void* vdata,size_t length) {
	char* data=(char*)vdata;
	uint64_t acc=0xffff;
	unsigned int offset=((uintptr_t)data)&3;
	if (offset) {
		size_t count=4-offset;
		if (count>length) count=length;
		uint32_t word=0;
		memcpy(offset+(char*)&word,data,count);
		acc+=ntohl(word);
		data+=count;
		length-=count;
	}
	char* data_end=data+(length&~3);
	while (data!=data_end) {
		uint32_t word;
		memcpy(&word,data,4);
		acc+=ntohl(word);
		data+=4;
	}
	length&=3;
	if (length) {
		uint32_t word=0;
		memcpy(&word,data,length);
		acc+=ntohl(word);
	}

	acc=(acc&0xffffffff)+(acc>>32);
	while (acc>>16) {
		acc=(acc&0xffff)+(acc>>16);
	}
	if (offset&1) {
		acc=((acc&0xff00)>>8)|((acc&0x00ff)<<8);
	}
	return htons(~acc);
}


int table_size( rtable_entry **rtable )
{
	int count = 0;
	rtable_entry *buf = rtable[count];
	while(buf != NULL)
	{
		count++;
		buf = rtable[count];
	}

	return count;
}

rtable_entry** sort_route_table(rtable_entry **rtable)
{
	int i = 0, j;	
  	while( rtable[i] != NULL )
  	{
  		j = i + 1;
  		while( rtable[j] != NULL )
  		{
  			if( (rtable[j]->prefix < rtable[i]->prefix) ||
  			((rtable[j]->prefix == rtable[i]->prefix) && (rtable[j]->mask < rtable[i]->mask)) )
  			{
  				rtable_entry *swap = rtable[j];
  				rtable[j] = rtable[i];
  				rtable[i] = swap;
  			}
			j++;
		}
		i++;
	}
	return rtable;
}



rtable_entry** read_route_table(rtable_entry **rtable)
{
	FILE *file = fopen("rtable.txt", "r");
	if( file == NULL ) 
	{
		printf("Couldn't open file\n");
		return NULL;
	}
	int i = 0;
  	while (1)  
  	{ 
		char prefix[15];
		char next_hop[15];
		char mask[15];
		int interface;

		if(fscanf(file, "%s", prefix) == EOF)
		{
			break;
		}
		fscanf(file, "%s", next_hop);
		fscanf(file, "%s", mask);
		fscanf(file, "%d", &interface);

		rtable = (rtable_entry**)realloc(rtable,(i+1) * sizeof(rtable_entry*));
		rtable[i] = (rtable_entry*)malloc(sizeof(rtable_entry));
		rtable[i]->prefix = inet_addr(prefix);
		rtable[i]->next_hop = inet_addr(next_hop);
		rtable[i]->mask = inet_addr(mask);
		rtable[i]->interface = interface;

		i++;
	}
	fclose(file);
	return rtable;
}



arp_entry** read_arp_table(arp_entry **arptable)
{
	FILE *file = fopen("arp_table.txt", "r");
	if( file == NULL ) 
	{
		printf("Couldn't open file\n");
		return NULL;
	}
	int i = 0;
  	while (1)  
  	{ 
		char ip[15];
		char mac[25];

		if(fscanf(file, "%s", ip) == EOF)
		{
			break;
		}
		fscanf(file, "%s", mac);

		arptable = (arp_entry**)realloc(arptable,(i+1) * sizeof(arp_entry*));
		arptable[i] = (arp_entry*)malloc(sizeof(arp_entry));
		arptable[i]->ip = inet_addr(ip);
		int check = hwaddr_aton(mac, arptable[i]->mac);
		DIE(check < 0, "No mac");
		i++;
	}
	fclose(file);
	return arptable;
}




rtable_entry* get_best_route(__u32 dest_ip, rtable_entry **rtable, int left, int right) 
// Implementat cu binary-search
{
	if( left <= right )
	{
		int middle =  left + ( (right - left) / 2 );
		if( (dest_ip & rtable[middle]->mask) == rtable[middle]->prefix )
		{
			while( (dest_ip & rtable[middle]->mask) == rtable[middle]->prefix )
			{
				middle++;
			}
			return rtable[middle-1];
		}
		if( (dest_ip & rtable[middle]->mask) < rtable[middle]->prefix )
		{
			return get_best_route(dest_ip, rtable, left, middle - 1);
		}
		if( (dest_ip & rtable[middle]->mask) > rtable[middle]->prefix )
		{
			return get_best_route(dest_ip, rtable, middle + 1, right);
		}
	}
	return NULL;
}




arp_entry* get_arp_entry(arp_entry **arptable, __u32 ip) 
{
	int i = 0;
    arp_entry *buf = arptable[i];
    while( buf != NULL ) 
    {
    	if( buf->ip == ip )
    	{
    		return buf;
    	}
    	i++;
    	buf = arptable[i];
    }
    return NULL;
}



int main(int argc, char *argv[])
{
	packet m; 
	int rc;

	init();

	rtable_entry **rtable = NULL;
	rtable = read_route_table(rtable);
	rtable = sort_route_table(rtable);
	// printf("%u  %u  %u  %d\n", rtable[0]->prefix,rtable[0]->next_hop,rtable[0]->mask,rtable[0]->interface);
	// printf("%u  %u  %u  %d\n", rtable[1]->prefix,rtable[1]->next_hop,rtable[1]->mask,rtable[1]->interface);
	// printf("%u  %u  %u  %d\n", rtable[2]->prefix,rtable[2]->next_hop,rtable[2]->mask,rtable[2]->interface);
	// printf("%u  %u  %u  %d\n", rtable[3]->prefix,rtable[3]->next_hop,rtable[3]->mask,rtable[3]->interface);

	arp_entry **arptable = NULL;
	arptable = read_arp_table(arptable);
	if( rtable == NULL ) 
	{
		return -1;
	}

	while (1) 
	{
		rc = get_packet(&m);
		DIE(rc < 0, "No message");
		struct ether_header *eth_h = (struct ether_header *)m.payload;

		if( eth_h->ether_type == htons(ETHERTYPE_ARP) )
		{
			continue;
		}
		else if( eth_h->ether_type == htons(ETHERTYPE_IP) )
		{
			struct iphdr *ip_h = (struct iphdr *)(m.payload + sizeof(struct ether_header));
			__u16 old = ip_h->check;
			ip_h->check = 0;
			__u16 new = ip_checksum(ip_h, sizeof(struct iphdr));

			if( new != old )
			{
				continue;
			}
			if( ip_h->ttl < 1 )
			{
				continue;
			}

			ip_h->ttl -= 1;
			ip_h->check = ip_checksum(ip_h, sizeof(struct iphdr));

			rtable_entry *best = get_best_route(ip_h->daddr, rtable, 0, table_size(rtable));
			if(best == NULL)
			{
				continue;
			}

			arp_entry *best_match = get_arp_entry(arptable, best->next_hop);
			if(best_match == NULL)
			{
				continue;
			}
			get_interface_mac(best->interface, eth_h->ether_shost);
			memcpy(eth_h->ether_dhost, best_match->mac, sizeof(best_match->mac));
			send_packet(best->interface, &m);

		}
	}
}
