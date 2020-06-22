### __Concepts Overview__

**Define federated learning. Draw a diagram to illustrate the main idea.**

Federated learning is a ML technique that trains an algorithm across multiple decentralised edge devices or servers that individually hold local data samples.

The data samples between nodes (edge devices) are not exchanged. Since FL allows us to build a common ML model without sharing data, it addresses various issues such as data privacy, data security, access rights and accessing heterogeneous data.

![Screen Shot 2020-06-12 at 1.01.33 am.png](resources/BE7DDD45364406BE07C83EDDE840EFE7.png =673x390)

FL may use a central server to coordinator different steps of the algorithm act as a reference clock. You can also have a P2P system between FL models.

The principle different to traditional approaches is that we do not assume the datasets from different edges are i.i.d and instead assume that they are heterogeneous and the size of the training data spans several orders of magnitude.

FL requires frequent communication between nodes during the learning process. Hence in addition to computing power, it requires high bandwidth connections to be able to exchange parameters of the ML model. 

Other challengers include heterogeneity between different local datasets, each node has some bias w.r.t the general population. Temporal heterogeneity is also an issue - each local dataset's distribution may vary with time.

Each node's dataset may require regular curations. 

FL is susceptible to backdoor attacks. 

---

**What are the 3 privacy principles used model re-training in federated learning?**

- __Focused collection:__ devices report only what is needed for computation
- __Ephemeral reports:__ the server never persists per-device reports
- __only-in-aggregate:__ the engineer can only access reports combined from several devices.

Note: ephemeral := lasting for a very short time

---

**Describe the federated averaging algorithm.**

We discuss the classic federated SGD and move into why federadted avg. works better.

Federated SGD is a variant of SGD for federated learning specifically. It takes in a random fraction of nodes, say $C$ and uses all the data in those chosen nodes.

These chosen nodes execute SGD independently and concurrently. At the end of each round, participants asynchronously share the gradients they computed for some of the parameters. 
Each participant has full control over which gradients to share and how often. 

For the centralised model, it takes in the sum of all gradients computed for a given parameter and determines the magnitude of global descent. 

Federated averaging allows local nodes to perform batch update on local data and exchange weights rather than the gradients. 

The justification for this is that if nodes start from the same initialisation averaging the gradients is strictly equivalent to averaging the weights themselves. Averaging tuned weights from the same initialisation does not necessarily hurt the resulting averaged model's performance.

According to the paper, there is a 23x decrease in communication rounds.

---

**Define secure aggregation and describe how it works.**

Secure aggregation is computing a multiparty sum of values/parameters without revealing each party's individual values/parameters or any of them at all.

The idea is that the server will see only the aggregated value and not the individual components, nor where the individual components came from.

Below is a diagram illustrating this.

![Screen Shot 2020-06-20 at 1.34.46 pm.png](resources/7997EE601F8E00EDA79F64C600E62893.png =747x368)

---

**Define differential privacy and describe how it works.**

Differential privacy is a system for publicly sharing information about a dataset by describing patterns of groups inside in dataset but there is no information that reveals which individuals are in the dataset.

An algorithm is said to be differentially private if an observer seeing its output cannot tell if a particular individual's information was used in the computation.

For FL, differential privacy plays a role by clipping weight updates to limit the contribution of an individual node and the server will add noise when combining updates.

![Screen Shot 2020-06-20 at 1.35.29 pm.png](resources/6F7E9D6EB3C0417B9C4CB30CF3437721.png =772x368)

---