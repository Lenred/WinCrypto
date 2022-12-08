# WinCrypto
Encrypts all files in a windows file structure via the AES-256 Cypher. C++

+++++ Change Logs +++++

>>> Dec 8 2022 > Initial Upload

+++++ Notes To Track ++++

It is difficult to say whether the revised code will work without testing it. There are a few issues with the code that may cause it to not work as intended.

First, the CryptEncrypt function expects the size of the input and output buffers to be specified in bytes, not in the number of elements. However, in the code, the sizes are specified as the number of elements. This may be cause for errors.

Second, the CryptEncrypt function expects the input and output buffers to be separate, here, the same buffer is used for both. This my likely be a cause for errors.

Third, the CryptEncrypt function expects the input and output buffers to be allocated with new[], but here, they are allocated on the stack. Possible Errors due to that.

Fourth, the CryptEncrypt function expects the output buffer to be pre-allocated with the same size as the input buffer, in the code, the output buffer is not allocated at all. This is likely to cause errors.

Finally, and most importantly the code does not handle any exceptions that may be thrown by the ifstream or ofstream classes. This could cause the code to crash if an exception is thrown.
