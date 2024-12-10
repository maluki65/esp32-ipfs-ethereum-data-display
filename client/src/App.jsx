import './App.css';
import React, { useState } from 'react';
import { ethers } from 'ethers'; // Correctly import ethers
import axios from 'axios';

const App = () => {
  const [walletAddress, setWalletAddress] = useState('');
  const [dataEntries, setDataEntries] = useState([]);
  const [error, setError] = useState('');
  const [contract, setContract] = useState(null);
  const [signer, setSigner] = useState(null);

  const hardcodedIpfsHash = 'QmQqhMAWnHqQCUcmc6fQKc7Q3HtAcaHasTBPaEbVygXCoN'; 

  const connectWallet = async () => {
    if (window.ethereum) {
      try {
        const provider = new ethers.BrowserProvider(window.ethereum);
        const accounts = await provider.send('eth_requestAccounts', []);
        const signer = await provider.getSigner(); // Ensure this is a signer instance
        const address = accounts[0];
  
        setWalletAddress(address);
        setSigner(signer);
  
        const contractAddress = '0x5fbdb2315678afecb367f032d93f642f64180aa3';
        const abi = [
          // Add your ABI here
         
        ];
  
        // Initialize the contract with a signer
        const contractInstance = new ethers.Contract(contractAddress, abi, signer);
        setContract(contractInstance); // Save the signer-enabled contract instance
  
        console.log('Wallet and contract connected successfully!');
      } catch (err) {
        console.error('Error connecting wallet:', err.message);
        setError('Failed to connect wallet. Please try again.');
      }
    } else {
      alert('MetaMask is not installed. Please install MetaMask and try again.');
    }
  };
  

  const storeHardcodedIpfsHash = async () => {
    if (contract) {
      try {
        const tx = await contract.storeData(hardcodedIpfsHash);
        console.log('Transaction sent:', tx);
        await tx.wait();
        alert('Hardcoded IPFS hash stored successfully!');
        setError('');
      } catch (err) {
        console.error('Error storing IPFS hash:', err.message);
        setError('Failed to store IPFS hash. Please try again.');
      }
    } else {
      setError('Please connect your wallet first.');
    }
  };

  const fetchData = async () => {
    if (contract) {
      try {
        const count = await contract.getDataCount();
        const entries = [];

        for (let i = 0; i < count; i++) {
          const result = await contract.getData(i);
          const ipfsHash = result[0];
          const timestamp = result[1];

          try {
            const response = await axios.get("https://ipfs.io/ipfs/QmQqhMAWnHqQCUcmc6fQKc7Q3HtAcaHasTBPaEbVygXCoN");
            entries.push({
              id: i,
              ipfsHash,
              timestamp,
              ipfsData: response.data,
            });
          } catch (ipfsError) {
            console.error(`Error fetching IPFS data for ${ipfsHash}:`, ipfsError);
            entries.push({
              id: i,
              ipfsHash,
              timestamp,
              ipfsData: 'Error fetching data from IPFS.',
            });
          }
        }

        setDataEntries(entries);
        setError('');
      } catch (err) {
        console.error('Error fetching data:', err.message);
        setError('Failed to fetch data. Please try again.');
      }
    } else {
      setError('Please connect your wallet first.');
    }
  };

  return (
    <div>
      <h1>FarmBlock Monitoring System</h1>

      {walletAddress ? (
        <button>{walletAddress.slice(0, 6)}...{walletAddress.slice(-4)}</button>
      ) : (
        <button onClick={connectWallet}>Connect Wallet</button>
      )}

      <button onClick={storeHardcodedIpfsHash} disabled={!walletAddress}>
        Store Hardcoded IPFS Hash
      </button>

      <button onClick={fetchData} disabled={!walletAddress}>
        Fetch Data
      </button>

      {error && <div style={{ color: 'red' }}>{error}</div>}

      {dataEntries.length > 0 && (
        <div>
          <h3>Fetched Data:</h3>
          <table border="1">
            <thead>
              <tr>
                <th>Data ID</th>
                <th>IPFS Hash</th>
                <th>Timestamp</th>
                <th>IPFS Content</th>
              </tr>
            </thead>
            <tbody>
              {dataEntries.map((entry, index) => (
                <tr key={index}>
                  <td>{entry.id}</td>
                  <td>{entry.ipfsHash}</td>
                  <td>{new Date(Number(entry.timestamp) * 1000).toLocaleString()}</td>
                  <td>{JSON.stringify(entry.ipfsData)}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
    </div>
  );
};

export default App;

