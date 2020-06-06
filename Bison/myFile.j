.class public test
.super java/lang/Object
.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 50
bipush 9
istore 1
ldc 1.200000
fstore 2
Label1:
fload 2
ldc 2.500000
if_icmpeq Label6
iload 1
fload 2
if_icmple Label2
iload 1
bipush 9
iadd
istore 1
goto Label5
Label2:
Label3:
iload 1
bipush 3
if_icmpge Label4
iload 1
bipush 1
iadd
istore 1
goto Label3
Label4:
Label5:
goto Label1
Label6:
return
.end method
