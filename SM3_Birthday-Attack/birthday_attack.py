# -*- coding: <encoding name> -*- : # -*- coding: utf-8 -*-

from pysmx.SM3 import SM3
import math
import os



def getRandomList(n, m):
	# 生成n个字m字节的字节串
	numbers = []
	while len(numbers) < n:
		i = os.urandom(m)
		if i not in numbers:
			numbers.append(i)
	return numbers


def brithAttack(m):
	sm3 = SM3()
	sqrt_m = int(math.sqrt(m * 8))
	list_k_value = []
	list_l_value = []
	# 生成 sqrt(8 * m)个的m长字节串
	list_k = getRandomList(sqrt_m, m)
	list_l = getRandomList(sqrt_m, m)
	for i in range(sqrt_m):
		# 计算出SM3值并放入集合
		sm3.update(list_k[i])
		item_k = sm3.hexdigest()
		list_k_value.append(item_k)

		sm3.update(list_l[i])
		item_l = sm3.hexdigest()
		list_l_value.append(item_l)

	print(list_k_value)
	print(list_l_value)
	# 求出合集
	coincide = set(list_k_value) & set(list_l_value)
	print(coincide)
	if not coincide:
		print("集合为空")
		return False
	else:
		for same in coincide:
			print(same)
		return True


if __name__ == '__main__':
	while True:
		if brithAttack(128):
			break
