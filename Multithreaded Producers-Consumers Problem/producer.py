"""
This module represents the Producer.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Thread
import time

class Producer(Thread):
    """
    Class that represents a producer.
    """

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        Thread.__init__(self)
        self.products = products
        self.marketplace = marketplace
        self.republish_wait_time = republish_wait_time
        self.p_id = 0


    def run(self):
        self.p_id = self.marketplace.register_producer()

        while self.marketplace.finished < self.marketplace.carts_nr \
        or self.marketplace.finished == 0:
        # produce cat timp nu au terminat toti cumparatorii
            for product in self.products:
                quantity = int(product[1])
                time_after_publish = product[2]
                for _ in range(quantity):
                    result = self.marketplace.publish(self.p_id, product[0])
                    # daca produsul nu a fost publicat, intra in bucla si reincearca dupa sleep
                    while result is False \
                    and self.marketplace.finished < self.marketplace.carts_nr:
                        time.sleep(self.republish_wait_time)
                        result = self.marketplace.publish(self.p_id, product)
                    time.sleep(time_after_publish)
