# No functionality yet, so require is commented out for now.
require 'libsocket/socket.rb'

# Monkey patch for until the library Ruby APi supports it
class Socket
  def connected?
    c_hook.socket_connected != 0
  end
end

def tick(args)
  if args.state.tick_count == 0
    $gtk.ffi_misc.gtk_dlopen("libsocket")
    Socket.include FFI::SOCKET
    args.state.socket = Socket.new '127.0.0.1', '7777'
    args.state.phase = :connecting
    $gtk.write_file('dr_output', 'loaded')
  end

  socket = args.state.socket
  socket.tick(args)

  case args.state.phase
  when :connecting
    args.outputs.labels << { x: 640, y: 360, text: 'Connecting...', alignment_enum: 1, vertical_alignment_enum: 1 }
    args.state.phase = :send if socket.connected?
  when :send
    append_to_test_output('connected')
    socket.c_send('Hello from DR')
    append_to_test_output('sent')
    args.state.phase = :receive
  when :receive
    # TODO
    $gtk.request_quit
  end

  if args.state.tick_count >= 600
    append_to_test_output('timeout')
    $gtk.request_quit
  end
end

def append_to_test_output(text)
  puts text
  $gtk.append_file('dr_output', ",#{text}")
end
