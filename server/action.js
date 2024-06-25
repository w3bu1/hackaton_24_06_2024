// Fonction asynchrone pour diffuser un message à tous les clients sauf l'expéditeur
async function sendMessage(clients, message, senderId = null) {
  for (const id in clients) {
    if (clients.hasOwnProperty(id) && id != senderId) {
      clients[id].write(message);
    }
  }
}

async function playRequest(clients, clientId) {
  const id = clientId == 2 ? 1 : 2;
  clients[id].write(`play ${id}\n`);
  clients[clientId].write(`play 0\n`);
  // await sendMessage(clients, id, `play ${id}\n`);
  // await sendMessage(clients, clientId, "play 0\n");
}

async function getClientCount(clients) {
  return Object.keys(clients).length;
}

async function communucateClients(clients, clientId, msg) {
  const timer = setTimeout(async () => {
    await sendMessage(clients, clientId == 1 ? 2 : 1, msg);
  }, 500);
  clearTimeout(timer);
}

module.exports = {
  sendMessage,
  playRequest,
  getClientCount,
  communucateClients,
};
