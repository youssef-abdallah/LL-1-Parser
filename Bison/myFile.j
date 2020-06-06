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
iload 1
bipush 5
if_icmple Label2
Label1: 
iload 1
bipush 10
if_icmpge Label3
iload 1
bipush 1
iadd
istore 1
goto Label1
goto Label3
Label2: 
bipush 10
istore 1
Label3: 
return
.end method
