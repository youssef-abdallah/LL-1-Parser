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
bipush 5
istore 1
iload 1
bipush 2
if_icmple Label1
bipush 0
istore 1
goto Label2
Label1: 
bipush 10
istore 1
Label2: 
return
.end method
