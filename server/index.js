const net = require("net");

let clients = {};
let clientId = 0;

const server = net.createServer((socket) => {
  if (Object.keys(clients).length == 2) id = 3;
  else id = clientId == 1 ? 2 : 1;
  clientId = id;
  const currentClientId = clientId;
  const clientAddress = `${socket.remoteAddress}:${socket.remotePort}`;
  clients[currentClientId] = socket;
  if (Object.keys(clients).length == 3) {
    sendMessageToClient(
      currentClientId,
      "Unable to connect, team already formed\n"
    );
    sendMessageToClient(currentClientId, "exit");
    delete clients[currentClientId];
    return;
  }
  console.log(
    `Client connected: ID = ${currentClientId}, Address = ${clientAddress}`
  );
  console.log(`Number of connected clients: ${Object.keys(clients).length}`);

  socket.on("data", (data) => {
    let id = currentClientId == 1 ? 2 : 1;
    console.log(`Received from ${currentClientId}: ${data}`);
    // Process the received data or send it back to the same client
    // Example: Send the received message back to the same client
    sendMessageToClient(id, data);
    // socket.write(`J'ai recu ca: ${data}`);
  });

  socket.on("end", () => {
    console.log(
      `Client disconnected: ID = ${currentClientId}, Address = ${clientAddress}`
    );
    delete clients[currentClientId];
    console.log(currentClientId);
    id = currentClientId == 1 ? 2 : 1;
    console.log(id);
    sendMessageToClient(id, "exit");
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);
  });

  socket.on("error", (err) => {
    console.error(`Socket error from ${currentClientId}: ${err}`);
    delete clients[currentClientId];
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);
  });
});

// Function to send a message to a specific client by ID
function sendMessageToClient(clientId, message) {
  if (clients[clientId]) {
    console.log("sending message to ", clientId);
    clients[clientId].write(message);
  } else {
    console.log(`Client with ID ${clientId} does not exist`);
  }
}

server.listen(8080, "0.0.0.0", () => {
  console.log("TCP server is listening on port 8080");
});
