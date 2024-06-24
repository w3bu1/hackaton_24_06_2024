const net = require("net");
const action = require("./action");

let clients = {};
let clientId = 0;

const server = net.createServer(async (socket) => {
  clientId++;
  const currentClientId = clientId;
  const clientAddress = `${socket.remoteAddress}:${socket.remotePort}`;
  clients[currentClientId] = socket;

  console.log(
    `Client connected: ID = ${currentClientId}, Address = ${clientAddress}`
  );
  console.log(`Number of connected clients: ${Object.keys(clients).length}`);

  if (Object.keys(clients).length >= 3) {
    await action.sendMessage(
      clients,
      currentClientId,
      "Unable to connect, team already formed\n"
    );
    await action.sendMessage(clients, currentClientId, "exit");
    // await sendMessageToClient(currentClientId, "exit");
    delete clients[currentClientId];
    clientId--;
    return;
  }

  if (Object.keys(clients).length === 2) {
    await action.playRequest(clients);
  }

  socket.on("data", async (data) => {
    let id = currentClientId === 1 ? 2 : 1;
    console.log(`Received from ${currentClientId}: ${data}`);
    await action.sendMessage(clients, id, data.toString());
    // await sendMessageToClient(id, data.toString());
  });

  socket.on("end", async () => {
    console.log(
      `Client disconnected: ID = ${currentClientId}, Address = ${clientAddress}`
    );
    delete clients[currentClientId];
    console.log(currentClientId);
    id = currentClientId === 1 ? 2 : 1;
    clientId--;
    console.log(id);
    await action.sendMessage(clients, id, "exit");
    // await sendMessageToClient(id, "exit");
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);
  });

  socket.on("error", (err) => {
    console.error(`Socket error from ${currentClientId}: ${err}`);
    delete clients[currentClientId];
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);
  });
});

// // Function to send a message to a specific client by ID
// async function sendMessageToClient(clientId, message) {
//   if (clients[clientId]) {
//     console.log(`Sending message to ${clientId}: ${message}`);
//     clients[clientId].write(message);
//   } else {
//     console.log(`Client with ID ${clientId} does not exist`);
//   }
// }

server.listen(8080, "0.0.0.0", () => {
  console.log("TCP server is listening on port 8080");
});
