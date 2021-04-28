
# from https://gist.github.com/Papierkorb/019ef4b330923175db4a7e6e54f4fb41
#
# This code is meant for debugging purposes. Its performance is probably bad,
# it's just meant to work for some hacky scripts you throw out tomorrow :)
# Create an instance of `Bitmap`, passing the file (IO or string), the width and height.
# Then push one (or more) 32bit pixels in ARGB format using `Bitmap#<<`.
# Pixel format is thus: 0xAARRGGBB (Alpha is highest byte, blue lowest).
# (Alpha is ignored by most programs however)
#
class Bitmap

  MAGIC = 'BM'

  def initialize(io, width, height, &block)

    io = File.open(io, "wb") if io.is_a?(String)
    @io = io
    @width = width
    @height = height

    write_header

    begin
      block.call(self)
    ensure
      close
    end if block
  end

  private def write_header

    bitmap_size = @width * @height * 4
    file_size = 54 + bitmap_size

    # Magic
    @io.write MAGIC

    # File size, Reserved, Offset to bitmap:
    @io.write [ file_size, 0, 54 ].pack('l<*')

    info = [
      40, # u32, biSize
      @width, # i32, biWidth
      -@height, # i32, biHeight
      1, # u16, biPlanes
      32, # u16, biBitCount
      0, # u32, biCompression
      bitmap_size, # u32, biSizeImage
      0, # i32, biXPelsPerMeter
      0, # i32, biYPelsPerMeter
      0, # u32, biClrUsed
      0, # u32, biClrImportant
    ]

    @io.write info.pack('L<l<l<S<S<l<l<L<L<l<l<')
  end

  def <<(argb)

    @io.write Array(argb).pack('l<*')

    self
  end

  def close

    @io.flush
    @io.close
  end
end

# Usage sample: 256x256 bitmap with a color gradient:
# Best piped through display: ruby bmp.rb | display -
# Or put something else than `STDOUT`.
#
#pic = Bitmap.new(STDOUT, 256, 256)
#
#256.times do |y|
#  c = y << 8 # Use the y as green channel
#  pic << Array.new(256){|i| c | i} # And x as blue channel.
#end
#
#pic.close # Done.

#Bitmap.new(STDOUT, 256, 256) do |bm|
#  256.times do |y|
#    c = y << 8 # Use the y as green channel
#    bm << Array.new(256){|i| c | i} # And x as blue channel.
#  end
#end

Bitmap.new(STDOUT, 1, 1) do |bm|
  bm << [ 0x002567 ]
end

