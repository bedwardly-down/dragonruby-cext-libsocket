require 'socket'

server = TCPServer.new(7777)

client = server.accept
request = client.gets
puts request
client.puts 'Hello from Ruby!'
client.close
