.source test.txt
.class public test
.super java/lang/Object

.method public <init>()V
aload_0
invokenonvirtual java/lang/Object/<init>()V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit locals 100
.limit stack 100
.line 1
bipush 5
istore 3
iload 3
bipush 10
if_icmple Label1
iload 3
bipush 1
iadd
istore 3
goto Label2
Label1: 
iload 3
bipush 1
isub
istore 3
Label2:
return
.end method
