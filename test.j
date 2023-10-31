.class public test
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
	.limit locals 1
	.limit stack 2
	bipush 10
	bipush 20
	imul
	bipush 30
	imul
	bipush 40
	imul
	bipush 50
	imul
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
