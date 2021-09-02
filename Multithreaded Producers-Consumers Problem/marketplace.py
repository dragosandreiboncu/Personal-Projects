#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2021
"""

from threading import Lock


class Marketplace:

    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """

    def __init__(self, queue_size_per_producer):
        self.queue_size_per_producer = queue_size_per_producer

        self.producers_nr = 0
        self.finished = 0

        self.producers_queue = {}  # dictionar de tipul: producator-nr_produse_distribuite

        self.products = []

        self.carts_nr = 0
        self.carts = []

        self.cons_mutex = Lock()
        self.prod_mutex = Lock()

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """

        p_id = self.producers_nr
        self.prod_mutex.acquire()
        self.producers_nr += 1
        self.prod_mutex.release()
        self.producers_queue[p_id] = 0  # fiecare consumator va avea initial 0 produse distribuite
        return p_id

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace
        """

        if self.producers_queue[producer_id] \
            < self.queue_size_per_producer:
            pair = (product, producer_id)  # adauga pe stoc perechi de produs-producator
            self.products.append(pair)
            self.prod_mutex.acquire()
            self.producers_queue[producer_id] += 1  # se adauga un produs la counter
            self.prod_mutex.release()
            return True
        return False

    def new_cart(self):
        """
        Creates a new cart for the consumer
        """

        cart_id = self.carts_nr
        cart = []
        self.carts.append(cart)
        self.cons_mutex.acquire()
        self.carts_nr += 1
        self.cons_mutex.release()
        return cart_id

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns
        """

        index = -1
        self.prod_mutex.acquire()
        for buffer in self.products:  # cauta produsul pe raft
            if product == buffer[0]:
                index = self.products.index(buffer)
        if index == -1:  # daca produsul nu se afla pe raft returneaza False
            self.prod_mutex.release()
            return False
        product_popped = self.products.pop(index)  # scoate de pe raft produsul
        producer_id = product_popped[1]
        self.producers_queue[producer_id] -= 1  # acum producatorul poate fabrica un produs in plus
        self.prod_mutex.release()

        # adauga in cos perechi de produs-producator

        self.carts[cart_id].append((product, producer_id))
        return True

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.
        """

        index = -1
        self.cons_mutex.acquire()
        for buffer in self.carts[cart_id]:  # cauta produsul in cos
            if product == buffer[0]:
                index = self.carts[cart_id].index(buffer)
        if index == -1:  # daca produsul nu se afla in cart returneaza nu se aplica nici o operatie
            self.cons_mutex.release()
            return
        product_popped = self.carts[cart_id].pop(index)  # scoate din cos produsul
        self.cons_mutex.release()
        self.prod_mutex.acquire()
        self.products.append(product_popped)  # adauga produsul inapoi pe raft

        # acum producatorul fabrica cu un produs mai puti

        self.producers_queue[product_popped[1]] += 1
        self.prod_mutex.release()

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.
        """

        self.cons_mutex.acquire()
        self.finished += 1  # counter pentru consumatorii ce au terminat cumparaturile
        self.cons_mutex.release()
        return self.carts[cart_id]
