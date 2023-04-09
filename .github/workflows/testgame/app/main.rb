# No functionality yet, so require is commented out for now.
# require 'libsocket/require.rb'

def tick(args)
  $gtk.ffi_misc.gtk_dlopen('libsocket')
  if FFI.const_defined?(:SOCKET)
    $gtk.write_file('success', 'success')
  else
    puts 'Failed to load libsocket'
  end
  $gtk.request_quit
end
