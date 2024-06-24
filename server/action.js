async function sendMessage(clients, clientId, message) {
  if (clients[clientId]) {
    console.log(`Sending message to ${clientId}: ${message}`);
    clients[clientId].write(message);
  } else {
    console.error(`Client with ID ${clientId} does not exist`);
  }
}

async function playRequest(clients) {
  await sendMessage(clients, 1, "play\n");
  await sendMessage(clients, 2, "play\n");
}

async function getClientCount(clients) {
  return Object.keys(clients).length;
}

module.exports = {
  sendMessage,
  playRequest,
  getClientCount,
};
