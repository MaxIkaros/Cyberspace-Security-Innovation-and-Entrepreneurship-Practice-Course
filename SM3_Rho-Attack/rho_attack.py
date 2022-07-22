# -*- coding: <encoding name> -*- : # -*- coding: utf-8 -*-
import os
from pysmx.SM3 import hash_msg


def rho_attack_f(n):
	h = os.urandom(int(n / 8))
	alist = []
	for i in range(0, int(n / 16)):
		alist.append(hash_msg(h)[:int(n / 4)])
		h = hash_msg(h)
		if hash_msg(h)[:int(n / 4)] in alist:
			print("Succeed!")
			return
	print("Failed")


def rho_attack(n):
	alist = []
	for i in range(0, int(n)):
		h = os.urandom(int(n / 8))
		b = hash_msg(h)[:int(n / 4)]
		if b in alist:
			print("Succeed!")
			break
		else:
			alist.append(b)
	print("Failed")


rho_attack(64)
