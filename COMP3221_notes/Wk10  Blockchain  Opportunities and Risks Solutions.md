### __Concepts Overview__

**What is the difference between trusted and trustworthy systems?**

A trusted system is a system that you have chosen to rely on fulfill a goal. When it fails you suffer harm or loss

A trustworthy system system is a system that can be shown to be secure and reliable pertaining to its specific goals. i.e. you have evidence that it will not fail.

---

**Briefly compare blockchains to conventional databases.**

The blockchain is logically centralised and physically and administratively decentralised.

Trade-offs

| | Blockchain |
|:---:|:---:|
|Integrity| + |
|Non-repudiation| + |
| Confidentiality, privacy | - |
| Modifiability | - |
| Throughput/scalability | - |
| Read/write | + - |
| Availability/latency | + - |

Note: repudiation: rejection of a proposal, denial of truth or validity.

---

**What are some complementary components to blockchains?**

Blockchains cannot do everything by themselves. Components that perform complementary /different functions to a blockchain are:

- UI for humans
- Legacy systems
- Big data
- Key management
- IoT integration

---

**What are some use cases for blockchain?**

- Supply chains
- Open data registeries
- Remittance payments

---

### __Case Studies__

**Describe the use case for supply chains.**

![Screen Shot 2020-06-19 at 11.43.39 pm.png](resources/3C3BFA91D2804170A9754D1AB1A71D81.png =1566x386)

- latency: refers to the logistics being confirmed and updated quickly so goods can move faster

- e.g. accountability of suppliers/producers of how and what they have produced. 
  - diamond industry: every diamond has an ID for each diamond and this prevents fraud. This is the gold standard that other industries have tried to replicate.

- Have a consortium Blockchain replicated to all participants and storing event data
- OR you can go EVEN further you can have the supply chain process coordinated on Blockchain as smart contracts.
- Smart contract: piece of code that is executed the code globally that impacts on what is already stored in the database. Usually its a write.

- Structure of supply chains similar to Blockchain
- Addresses limitations on visibility and logistics efficiency
- Provenance (origins) and supply chain quality
- Attach financial contracts to the logistics contracts

---

**Describe the open data registeries use case.**

- Big push of gov't to have open data sets
- Legal problems: malicious corruption, confidentiality, authorisation, permissions etc.
- Right now its just a giant repository.
- Portability

 You can have 2 main types, a public blockchain where the data agency controls only entries in the official index, or a consortium across agencies so that public access can be controlled through a portal.
 
 ![Screen Shot 2020-06-19 at 11.59.20 pm.png](resources/7FA8D01D5B1A44CE3D4646D272DCB199.png =522x366)

---

**Describe the use case for remittance payments.**

The current way to do remittance payments is as follows:

![Screen Shot 2020-06-20 at 12.01.05 am.png](resources/E69A0096133CAE5E8BAA4A7F76D0E04E.png =763x363)

As of now, the cost transparency is very low for remittance payments and also it takes a while to transfer this money.

Now, how do we ensure the money is legal? This is the biggest issue - regulators need to check for money laundering. 

Note: KYC := "know your chains"

![Screen Shot 2020-06-20 at 12.02.51 am.png](resources/39577599F3E10108CA9D0A2C56F5E8A4.png =517x697)

---

### __Adopting Blockchains__

**What is the biggest issue with adopting Blockchains?**

Security. If you use a Blockchain for critical functions, it will be subject to attack. Also, we should never assume that networks are good. We should assume networks are full of failures and potential malicious attacks.

Furthermore, we need to think about Blockchain governance.

---

**What are some myths of Blockchains?**

| Myth | Reality |
|:---:|:---:|
| Solves every problem | Just a database |
| Trustless | can shift trust and spread trust (majority) |
| Secure | Focus on integrity not confidentiality |
| Smart contracts are legal contracts | May help execute parts of some legal contracts |
| Immutable | Offers only probabilistic immutability |
| Waste electricity | Emerging blockchains are more efficient |
| Inherently unscalable | Emerging blockchains are more scalable |
| If beneficial, will be adopted | Adoption can be hampered by FUD |

Note: FUD := fear, uncertainty and doubt.

---

**What are some research directions of Blockchain?**

- "programmable money"?
- blockchain vulnerability
- formal verification (Isabelle)
- specification (deontic defeasible)
- supply chains

---

### __Attacking the Blockchain__

**Describe "man-in-the-middle" attacks**

A "man-in-the-middle" attack is when the attacker is intercepting the victim's communications. 

There were two such examples - one is when the attacker acted as the mining pool and claims the miner's rewards for themselves, and the miners did not receive their reward.

The second example is when users were directed to a phishing site and had their coins stolen.

---

**Describe the "double-spending" attack.**

Forks of the blockchain have inconsistent transactions and we don't know which one is legitimate.

For double-spending, the two blocks must have conflicting transactions. E.g. transaction of bitcoin and physical items.

Then if the physical items were already received but the transaction was on an invalid block that is not committed to the main chain, then there will be a double-spending.

---

**What are mining pools?**

A group of people that gather together to share their computational power and share the rewards.

There is a central system that distributed the hashing functions to the individual miners and the pool distributed the reward.

The issue with this is that you don't know where the miners are.

Someone from Sydney could connect to a pool in China, Europe etc.

Below is a snapshot of the biggest minining pools for Blockchain.

![Screen Shot 2020-06-20 at 1.00.24 am.png](resources/AC37CA8B4D3BD79B416397D794DE3F5F.png =960x661)

This is a bit ironic since a Blockchain is supposed to be a distributed, peer-verified network but the mining power is gradually being centralised.

Furthermore, if you look at the pool of Ethereum miners, you'll notice that they are all interconnected. Indeed, amongst the 10 largest pools of mining pools, 7 of them rely on a particular group called AS and represent about 87% of the mining power.

![Screen Shot 2020-06-20 at 1.04.48 am.png](resources/5A677887754D5D4BA4CE39A9EADF2529.png =570x410)

It's highly unlikely in this case we can do any attacks since the connections between the ASes used by the major public pools are so strong, it will be difficult to partition the network in order to double spend.

---

**Define a consortium Blockchain.**

A consortium blockchain is a semi-private blockchain that has an access control layer to govern who has access to the network. In contrast to public blockchain networks, validators on private blockchains are vetted by the network owner and do not rely on anonymous nodes to validate transactions.

There is no mining pool in a consortium environment and notes have the same amount of resources hence computational power.

---

**How are Ethereum block creation difficulty adjusted? How do we take advantage of this to attack an eumulated consortium Ethereum blockchain?** 

Ethereum block difficulty levels are adjusted very frequently in order to keep block creation levels to roughly 12-13 seconds per block. This is exploited since the blockchain wants to maintain a block creation speed and thus makes difficulty easier. Then the miners with less computational power has a much higher chance relative to a stronger miner to create a block.

We set up the adversary similar to how we would attack a public blockchain.

![Screen Shot 2020-06-20 at 1.22.30 am.png](resources/49A9A3748D9DA8BBF35CBE2B53374705.png =865x344)

Essentially a successful attack is when we add a transaction and wait for `k=12` blocks to be appended afterwards, which Ethereum then considers the block holding the transaction comitted and the trade is made official i.e. the block becomes immutable. However, later on the transaction disappears because it will be overwritten by the correct branch. However, the physical goods have already been exchanged.

Below is a graph of the success rate of attacks.

![Screen Shot 2020-06-20 at 1.12.05 am.png](resources/06F23E767463F50267B7BA27C5EADAF3.png =710x260)

---

**How does this work for private blockchain?**

The main difference is that the VMs are linked by a Ethernet switch in a private blockchain.

![Screen Shot 2020-06-20 at 1.23.35 am.png](resources/E6097A3A6F7761502D1CAD5FFC2AEC16.png =712x518)

Then we can do ARP spoofing to become a man-in-the-middle and partition the network.

---