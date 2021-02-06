"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.webSocketServer = exports.server = exports.port = void 0;
const http_1 = __importDefault(require("http"));
const app_1 = require("./app");
const udphostport_1 = require("./models/udphostport");
const mongoclient_1 = require("./models/mongoclient");
const createdbconnection_1 = require("./controllers/db/createdbconnection");
const passosctowebsockets_1 = require("./controllers/passosctowebsockets");
const osc = require("osc");
const port = 5000;
exports.port = port;
const server = http_1.default.createServer(app_1.app);
exports.server = server;
const webSocketServer = require("socket.io")(server);
exports.webSocketServer = webSocketServer;
// const hostUdpPort = new osc.UDPPort({
//     localAddress: "159.203.191.234",
//     localPort: 57121,
//     metadata: true
// })
if (process.env.NODE_ENV != "test") {
    server.listen(port, () => {
        console.log(`app listening at port: ${port}`);
        udphostport_1.udpHostPort.open();
        createdbconnection_1.createDbConnection(mongoclient_1.database, mongoclient_1.dbURI, mongoclient_1.dbOptions);
        udphostport_1.udpHostPort.on("ready", () => console.log("osc started"));
        udphostport_1.udpHostPort.on("error", (err) => console.log(err));
        udphostport_1.udpHostPort.on("message", (m) => console.log(m));
        passosctowebsockets_1.passOscToWebsockets();
    });
}
