declare void @printInt(i32)
define i32 @main() {
	call void @printInt(i32 42)
	ret i32 0
}