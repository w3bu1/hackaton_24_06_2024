const express = require("express");
const bodyParser = require("body-parser");
const action = require("./action");

const app = express();
app.use(bodyParser.json());

let clients = {};
let clientId = 0;

app.post("/connect", async (req, res) => {
  if (Object.keys(clients).length >= 2) {
    return res.status(400).send("Unable to connect, team already formed");
  }

  clientId++;
  const currentClientId = clientId;
  clients[currentClientId] = res;

  console.log(`Client connected: ID = ${currentClientId}`);
  console.log(`Number of connected clients: ${Object.keys(clients).length}`);

  if (Object.keys(clients).length === 2) {
    await action.playRequest(clients);
  }

  req.on("close", () => {
    console.log(`Client disconnected: ID = ${currentClientId}`);
    delete clients[currentClientId];
    clientId--;
    console.log(`Number of connected clients: ${Object.keys(clients).length}`);
  });
});

app.post("/message", async (req, res) => {
  const { id, message } = req.body;
  const client = clients[id];
  if (client) {
    await action.sendMessage(clients, id, message);
    res.send("Message sent");
  } else {
    res.status(404).send("Client not found");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
