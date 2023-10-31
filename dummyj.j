.class public dummyj
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
	.limit locals 3
	.limit stack 2
	bipush 42
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokevirtual java/io/PrintStream/println(I)V
	getstatic java/lang/System/out Ljava/io/PrintStream;
	bipush 45
	invokevirtual java/io/PrintStream/println(I)V
	iconst_3
	iconst_4
	iadd
	getstatic java/lang/System/out Ljava/io/PrintStream;
	swap
	invokevirtual java/io/PrintStream/println(I)V
	iload_0
	istore_1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	iload_0
	iconst_5
	isub
	istore_1
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_1
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
