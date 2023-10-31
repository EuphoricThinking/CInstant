declare void @printInt(i32)
define i32 @main() {
	%a = alloca i32
	store i32 1, i32* %a
	%load_0 = load i32, i32* %a
	call void @printInt(i32 %load_0)
	%b = alloca i32
	store i32 2, i32* %b
	%load_1 = load i32, i32* %b
	call void @printInt(i32 %load_1)
	%c = alloca i32
	store i32 3, i32* %c
	%load_2 = load i32, i32* %c
	call void @printInt(i32 %load_2)
	%d = alloca i32
	store i32 4, i32* %d
	%load_3 = load i32, i32* %d
	call void @printInt(i32 %load_3)
	ret i32 0
}