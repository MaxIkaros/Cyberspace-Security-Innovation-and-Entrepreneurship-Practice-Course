#!/usr/bin/env python
# -*- coding:utf-8 -*-

from gmssl import sm3, func
import sm3_mod
import struct
import os


def generate_guess_hash(old_hash, secret_len, append_m):
	vectors = []
	message = ""
	# Group OLD_HASH, 8 bytes in each group, and to integer
	for r in range(0, len(old_hash), 8):
		vectors.append(int(old_hash[r:r + 8], 16))

	# forge
	if secret_len > 64:
		for i in range(0, int(secret_len / 64) * 64):
			message += '1'
	for i in range(0, secret_len % 64):
		message += '1'
	message = func.bytes_to_list(message)
	message = padding(message)
	message.extend(func.bytes_to_list(append_m))
	return sm3_mod.sm3_hash(message, vectors)


def padding(msg):
	mlen = len(msg)
	msg.append(0x80)
	mlen += 1
	tail = mlen % 64
	range_end = 56
	if tail > range_end:
		range_end = range_end + 64
	for i in range(tail, range_end):
		msg.append(0x00)
	bit_len = (mlen - 1) * 8
	msg.extend([int(x) for x in struct.pack('>q', bit_len)])
	for j in range(int((mlen - 1) / 64) * 64 + (mlen - 1) % 64, len(msg)):
		global pad
		pad.append(msg[j])
		global pad_ms
		pad_ms += str(hex(msg[j]))
	return msg


secret = os.urandom(16)
# secret = str(random.random())
secret_hash = sm3.sm3_hash(func.bytes_to_list(secret))
secret_len = len(secret)
add_m = b"202000460062"  # Additional Information
pad_ms = ""  # padding in attack
pad = []
print("secret: {}".format(secret))
print("Secret length:{}".format(len(secret)))
print("Secret hash:" + secret_hash)
print("Additional information:", add_m)

guess_hash = generate_guess_hash(secret_hash, secret_len, add_m)
new_msg = func.bytes_to_list(secret)
new_msg.extend(pad)
new_msg.extend(func.bytes_to_list(add_m))
new_msg_str = secret + pad_ms.encode('utf-8') + add_m

new_hash = sm3.sm3_hash(new_msg)

print("Constructed text hash:" + guess_hash)
print("<<<------------------------------------------------------------>>>")
print("Verify whether it is successful")
print("Calculate 'hash(secret+padding+m)' ")
print("New message:\n {}".format(new_msg_str))
print("Calculate hash(new message):" + new_hash)
if new_hash == guess_hash:
	print("Success!")
else:
	print("Fail..")
