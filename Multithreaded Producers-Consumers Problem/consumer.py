"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time

class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        Thread.__init__(self)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time
        self.c_id = 0
        self.name = kwargs['name']

    def run(self):
        self.c_id = self.marketplace.new_cart()

        for cart in self.carts:
            for product in cart:
                quantity = int(product['quantity'])
                for _ in range(quantity):
                    if product['type'] == "add":
                        result = self.marketplace.add_to_cart(self.c_id, product['product'])
                    # daca produsul nu se gaseste pe raft, intra in bucla si reincearca dupa sleep
                        while result is False:
                            time.sleep(self.retry_wait_time)
                            result = self.marketplace.add_to_cart(self.c_id, product['product'])
                    elif product['type'] == "remove":
                        self.marketplace.remove_from_cart(self.c_id, product['product'])
        # print
        orders = self.marketplace.place_order(self.c_id)
        for product in orders:
            print(self.name + " bought " + str(product[0]))
