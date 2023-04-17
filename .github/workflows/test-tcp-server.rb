require 'logger'
require 'socket'

logger = Logger.new(STDOUT)
logger.formatter = proc do |_severity, datetime, _progname, msg|
  time = datetime.strftime('%Y-%m-%d %H:%M:%S')
  "[Test TCP Server] #{time} -- #{msg}\n"
end

server = TCPServer.new(7777)
logger.info 'Listening on port 7777'

client = server.accept
logger.info 'Client connected'
request = client.gets
logger.info request
client.puts 'Hello from Ruby!'
client.close
logger.info 'Client disconnected'

server.close
logger.info 'Server closed'
