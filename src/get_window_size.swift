import Cocoa

@_cdecl("get_screen_size")
public func get_screen_size(_ x: UnsafeMutablePointer<Int>, _ y: UnsafeMutablePointer<Int>)
{
	let screenRect = NSScreen.main?.visibleFrame ?? NSRect.zero

	let contentRect = NSRect(x: 0, y: 0, width: 100, height: 100)
	let frameRect = NSWindow.frameRect(forContentRect: contentRect, styleMask: .titled)
	let titleBarHeight = frameRect.height - contentRect.height
	x.pointee = Int(screenRect.size.width)
	y.pointee = Int(screenRect.size.height - titleBarHeight)
}
