# ESP32 Data Pipeline with IPFS and Ethereum Smart Contract

This project demonstrates how an ESP32 device collects sensor data (temperature, humidity, and GPS), sends it to Pinata IPFS for decentralized storage, and integrates with a React app to manage and visualize the data. The React app retrieves the IPFS hash, interacts with an Ethereum smart contract via MetaMask, and fetches the data from IPFS for display in a table format.

---

## Table of Contents
- [Architecture Overview](#architecture-overview)
- [Features](#features)
- [Requirements](#requirements)
- [Setup Instructions](#setup-instructions)
  - [Step 1: Clone the Repository](#step-1-clone-the-repository)
  - [Step 2: Install Dependencies](#step-2-install-dependencies)
  - [Step 3: Run Hardhat Node Locally](#step-3-run-hardhat-node-locally)
  - [Step 4: Deploy the Smart Contract](#step-4-deploy-the-smart-contract)
  - [Step 5: Setup the React App](#step-5-setup-the-react-app)
  - [Step 6: Configure ESP32 Device](#step-6-configure-esp32-device)
- [License](#license)

---

## Architecture Overview

1. **ESP32 Device**:
   - Collects data (temperature, humidity, GPS).
   - Sends data to Pinata IPFS for storage.

2. **Pinata IPFS**:
   - Decentralized storage platform for sensor data.
   - Generates an IPFS hash for the stored data.

3. **Ethereum Smart Contract**:
   - Receives and stores the IPFS hash.
   - Uses MetaMask for transaction signing.

4. **React Frontend**:
   - Retrieves the IPFS hash from the smart contract.
   - Fetches and displays the actual data from IPFS.

---

## Features

- Data collection from DHT22 and GPS sensors via ESP32.
- Decentralized storage using Pinata IPFS.
- Blockchain integration with Ethereum and MetaMask.
- Data visualization in a React app.

---

## Requirements

- [Node.js](https://nodejs.org/)
- [Hardhat](https://hardhat.org/)
- MetaMask browser extension
- ESP32 device
- DHT22 sensor and GPS module
- React environment (Vite recommended)

---

## Setup Instructions
## Run Hardhat Node Locally
To simulate an Ethereum blockchain locally:
 -npx hardhat node
This will create a local Ethereum network and provide pre-funded accounts for testing.
## Deploy the Smart Contract
Deploy the contract to the local network:
npx hardhat run scripts/deploy.js --network localhost
Note the contract address from the deployment logs. Update your React app's configuration to use this address.
## Connecting MetaMask Wallet to Hardhat Local Node
To connect MetaMask to the local Hardhat blockchain network and use the accounts provided by Hardhat:

Step 1: Add the Hardhat Local Network to MetaMask
Open MetaMask in your browser.
Click on the profile icon (top-right) and select Settings > Networks > Add a network.
Fill in the network details:
Network Name: Hardhat Local
New RPC URL: http://127.0.0.1:8545
Chain ID: 31337 (Default Hardhat network chain ID)
Currency Symbol: ETH
Block Explorer URL: Leave blank
Click Save.
Step 2: Import Hardhat Accounts into MetaMask
Hardhat provides pre-funded accounts when running a local node. These accounts are listed in the terminal after you run:


Accounts:
0x5FbDB2315678afecb367f032d93F642f64180aa3 (Private key: 0x...1)
0xABe31b2818A5... (Private key: 0x...2)
Copy one of the private keys from the list.

In MetaMask:

Click on the profile icon.
Select Import Account.
Paste the private key into the input box.
Click Import.
Repeat this process for other accounts as needed.

Step 3: Test the Connection
In MetaMask, ensure that the active network is Hardhat Local.
Use the imported account to sign transactions and interact with the deployed smart contract in the React app.
Additional Notes
Switching Networks: When switching from Hardhat Local to another network (e.g., Mainnet or Testnet), ensure that MetaMask is configured for the desired network to avoid errors.
Local Network Reset: If you restart the Hardhat node, the accounts and their balances will reset. Re-import the accounts if needed.
### Step 1: Clone the Repository
```bash
git clone https://github.com/yourusername/esp32-ipfs-eth-integration.git
cd esp32-ipfs-eth-integration

