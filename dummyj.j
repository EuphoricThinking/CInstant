.class public dummyj
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
	.limit locals 2
	.limit stack 2
	bipush 42
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokevirtual java/io/PrintStream/println(I)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 45
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
