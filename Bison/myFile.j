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
iload 1
bipush 5
if_icmple Label6
iload 1
bipush 10
if_icmple Label5
Label4:
iload 1
bipush 10
if_icmple Label7
iload 1
bipush 1
isub
istore 1
goto Label4
goto Label7
Label5:
bipush 10
istore 1
goto Label7
Label6:
bipush 5
istore 1
Label7:
iload 1
bipush 1
iadd
istore 1
Label8:



return
.end method
