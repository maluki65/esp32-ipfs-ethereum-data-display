// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract SensorDataStorage {
    struct SensorData {
        string ipfsHash; // On storing IPFS hash 
        uint256 timestamp; // Timestamp of the record
    }

    mapping(uint256 => SensorData) public data; // Mapping to store data by an ID
    uint256 public dataCount; // Counter for stored data entries

    event DataStored(uint256 id, string ipfsHash, uint256 timestamp);

    // Store IPFS hash in the contract
    function storeData(string memory _ipfsHash) public {
        data[dataCount] = SensorData(_ipfsHash, block.timestamp);
        emit DataStored(dataCount, _ipfsHash, block.timestamp);
        dataCount++;
    }

    // Retrieve data by ID
    function getData(uint256 _id) public view returns (string memory, uint256) {
        SensorData memory sensorData = data[_id];
        return (sensorData.ipfsHash, sensorData.timestamp);
    }

    // Get the total number of data entries stored
    function getDataCount() public view returns (uint256) {
        return dataCount; // Return the total count of data entries
    }
}
/*contract SensorDataStorage {
    // Struct to store SensorData with an IPFS hash and timestamp
    struct SensorData {
        bytes32 ipfsHash; // Use bytes32 instead of string to store the hash more efficiently
        uint256 timestamp; // Timestamp of when the data was recorded
    }

    // Mapping to store data entries by their unique ID
    mapping(uint256 => SensorData) public data;
    uint256 public dataCount; // Counter to track the number of data entries

    // Event to log the data storage
    event DataStored(uint256 id, bytes32 ipfsHash, uint256 timestamp);

    // Function to store IPFS hash in the contract (takes a bytes32 hash)
    function storeData(bytes32 _ipfsHash) public {
        data[dataCount] = SensorData(_ipfsHash, block.timestamp);
        emit DataStored(dataCount, _ipfsHash, block.timestamp); // Emitting the event to log the storage action
        dataCount++; // Increment the data count
    }

    // Function to retrieve data by ID
    function getData(uint256 _id) public view returns (bytes32, uint256) {
        SensorData memory sensorData = data[_id];
        return (sensorData.ipfsHash, sensorData.timestamp); // Returning the stored IPFS hash and timestamp
    }

    // Function to retrieve the total number of data entries stored
    function getDataCount() public view returns (uint256) {
        return dataCount; // Returning the total count of data entries
    }
}*/
