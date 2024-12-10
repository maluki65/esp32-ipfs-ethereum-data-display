async function main() {
  const [deployer] = await ethers.getSigners();
  console.log("Deploying the contract with the account:", deployer.address);

  const SensorDataStorage = await ethers.getContractFactory("SensorDataStorage");
  const sensorDataStorage = await SensorDataStorage.deploy();

  console.log("sensorDataStorage contract deployed to:", await sensorDataStorage.getAddress());
}

main()
  .then(() => process.exit(0))
  .catch((error) => {
      console.error(error);
      process.exit(1);
  });
