# MPT Research Report

------

## 概述

Merkle Patricia Tree（又称为Merkle Patricia Trie，简称MPT树）是一种经过改良的、融合了Merkle Tree和Radix Trie两种树结构优点的数据结构，是以太坊中用来组织管理账户数据、生成交易集合哈希的重要数据结构。

MPT树有以下几个作用：

- 存储任意长度的key-value键值对数据，符合以太坊的state模型；
- 提供了一种快速计算所维护数据集哈希标识的机制；
- 提供了快速状态回滚的机制；
- 提供了一种称为默克尔证明的证明方法，进行轻节点的扩展，实现简单支付验证；

由于MPT结合了Radix trie和Merkle Tree两种树结构的特点与优势 ，因此，在介绍MPT之前需要知道这两种树结构的特点。

