.class public stack_limit
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
	.limit locals 2
	.limit stack 2
	iconst_1
	iconst_1
	isub
	iconst_1
	swap
	isub
	iconst_1
	swap
	isub
	iconst_1
	swap
	isub
	istore_0
	getstatic java/lang/System/out Ljava/io/PrintStream;
	iload_0
	invokevirtual java/io/PrintStream/println(I)V
	return
.end method
