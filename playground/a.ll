declare void @printInt(i32)
define i32 @main() {
	%a = alloca i32
	store i32 42, i32* %a
	%load_a = load i32, i32* %a
	call void @printInt(i32 %load_a)
	ret i32 0
}