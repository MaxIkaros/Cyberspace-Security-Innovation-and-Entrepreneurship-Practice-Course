# -*- coding: <encoding name> -*- : # -*- coding: utf-8 -*-

from pysmx.SM3 import SM3
import math
import os



def getRandomList(n, m):
	# ����n����m�ֽڵ��ֽڴ�
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
	# ���� sqrt(8 * m)����m���ֽڴ�
	list_k = getRandomList(sqrt_m, m)
	list_l = getRandomList(sqrt_m, m)
	for i in range(sqrt_m):
		# �����SM3ֵ�����뼯��
		sm3.update(list_k[i])
		item_k = sm3.hexdigest()
		list_k_value.append(item_k)

		sm3.update(list_l[i])
		item_l = sm3.hexdigest()
		list_l_value.append(item_l)

	print(list_k_value)
	print(list_l_value)
	# ����ϼ�
	coincide = set(list_k_value) & set(list_l_value)
	print(coincide)
	if not coincide:
		print("����Ϊ��")
		return False
	else:
		for same in coincide:
			print(same)
		return True


if __name__ == '__main__':
	while True:
		if brithAttack(128):
			break
