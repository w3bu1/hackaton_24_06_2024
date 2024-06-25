const net = require("net");
const action = require("./action");

let clients = {};
let clientId = 0;

// Créer un serveur TCP
const server = net.createServer((socket) => {
  if (Object.keys(clients).length >= 2) {
    // Refuser la connexion si déjà deux clients sont connectés
    console.log(`Connection refused: Only two clients are allowed.`);
    socket.write("Server full: Only two clients are allowed.\n");
    socket.end();
    return;
  }

  clientId++;
  const currentClientId = clientId;
  const clientAddress = `${socket.remoteAddress}:${socket.remotePort}`;
  clients[currentClientId] = socket;

  console.log(
    `Client connected: ID = ${currentClientId}, Address = ${clientAddress}`
  );
  console.log(`Number of connected clients: ${Object.keys(clients).length}`);

  if (Object.keys(clients).length == 2)
    action.playRequest(clients, currentClientId);
  // Informer tous les clients de la nouvelle connexion
  action.sendMessage(clients, `Client ${currentClientId} has connected\n`);

  // Gérer les données reçues
  socket.on("data", async (data) => {
    console.log(`Received from ${currentClientId}: ${data}`);
    await action.sendMessage(clients, `${data.toString()}\n`, currentClientId);
    if (!data.toString().includes("combo"))
      await action.playRequest(clients, currentClientId);
  });

  // Gérer la fin de la connexion
  socket.on("end", async () => {
    console.log(
      `Client disconnected: ID = ${currentClientId}, Address = ${clientAddress}`
    );
    delete clients[currentClientId];
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);

    // Informer tous les clients de la déconnexion
    await action.sendMessage(
      clients,
      `Client ${currentClientId} has disconnected\n`
    );

    // Envoyer un message "exit" à l'autre client connecté
    if (Object.keys(clients).length === 1) {
      const remainingClientId = Object.keys(clients)[0];
      await sendMessageToClient(remainingClientId, "exit");
      clientId = 0;
    }
  });

  // Gérer les erreurs de socket
  socket.on("error", async (err) => {
    console.error(`Socket error from ${currentClientId}: ${err}`);
    delete clients[currentClientId];
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);

    // Envoyer un message "exit" à l'autre client connecté en cas d'erreur
    if (Object.keys(clients).length === 1) {
      const remainingClientId = Object.keys(clients)[0];
      await sendMessageToClient(remainingClientId, "exit");
      clientId = 0;
    }
  });
});

server.listen(8080, "0.0.0.0", () => {
  console.log("TCP server is listening on port 8080");
});

// Fonction asynchrone pour envoyer un message à un client spécifique par ID
async function sendMessageToClient(clientId, message) {
  if (clients[clientId]) {
    clients[clientId].write(message);
  } else {
    console.log(`Client with ID ${clientId} does not exist`);
  }
}
