/*
    TF-IDF (Term Frequency - Inverse Document Frequency) = Defines relevance of a term (t) in a document (d) in available collection of documents (D)
    Example: 
        - Doc1 (1000 words) -> about elasticsearch guide
        - Doc2 (5000 words) -> about a criminal who used elastic search
        => the relevance of term "elasticsearch" in Doc1 is more than Doc2
        => the relevance of term "guide" in Doc1 is very less because "guide" can be of any type like manual, setup, etc.

    TF-IDF(t, d, D) = TF(t,d) * IDF(t,D)
*/

const collection = [
    {
        title: "product review phone",
        data: "i bought this phone last week the battery life is excellent and lasts all day with regular usage such as calls messaging and video streaming the camera quality is decent for the price however the phone heats slightly during gaming"
    },
    {
        title: "food review",
        data: "i visited this restaurant yesterday the food was good especially the butter chicken and naan the service was slightly slow and the waiting time was around twenty minutes the prices are reasonable overall it is a good place to visit"
    },
    {
        title: "work email",
        data: "the deployment is scheduled for tomorrow at ten in the morning please ensure that all pending pull requests are reviewed and merged before the end of the day inform the team if there are any blockers"
    },
    {
        title: "chat message",
        data: "i tried a new artificial intelligence tool that helps in writing code it saved a significant amount of time however it is not perfect and required some debugging"
    },
    {
        title: "travel experience",
        data: "i recently visited manali the weather was pleasant and the mountains were beautiful the roads were not in good condition which made travel tiring overall the experience was worthwhile"
    },
    {
        title: "ecommerce complaint",
        data: "the product delivery was delayed and the packaging was damaged customer support was not responsive this resulted in a poor shopping experience"
    },
    {
        title: "fitness post",
        data: "i started going to the gym regularly the initial days were challenging but now i feel more energetic maintaining a proper diet is still difficult"
    },
    {
        title: "tech blog snippet",
        data: "microservices architecture allows independent scaling of system components however it introduces complexity in areas such as service communication retries and monitoring it may not be suitable for small projects"
    }
];

const totalDocs = collection.length;
const allTerms = new Set();
const termPerDocFreqArr = [];
const docLenArr = [];

for (let doc of collection) {
    const terms = doc.data.split(' ')
    for (let term of terms) {
        allTerms.add(term)
    }
    const termPerDocFreq = terms.reduce((currTermFreq, term) => {
        if (term in currTermFreq) {
            currTermFreq[term] = currTermFreq[term] + 1;
        } else {
            currTermFreq[term] = 1;
        }
        return currTermFreq;
    }, {});
    termPerDocFreqArr.push(termPerDocFreq);
    docLenArr.push(terms.length);
}

const termCollectionFreq = {};

for (let doc of collection) {
    const terms = doc.data.split(' ');
    for (let term of allTerms) {
        if (terms.includes(term)) {
            if (term in termCollectionFreq) {
                termCollectionFreq[term] = termCollectionFreq[term] + 1;
            } else {
                termCollectionFreq[term] = 1;
            }
        }
    }
}

for (let i = 0; i < totalDocs; i += 1) {
    let calcData = [];
    const termPerDocFreq = termPerDocFreqArr[i];
    const totalTerms = docLenArr[i];
    for (let term in termPerDocFreq) {
        let freq = termPerDocFreq[term];
        let TF = freq / totalTerms;
        let IDF = Math.log(totalDocs / termCollectionFreq[term]);
        let TF_IDF = TF * IDF;
        calcData.push({ term, tf_idf: TF_IDF });
    }


    calcData.sort((a, b) => {
        return b.tf_idf - a.tf_idf;
    });

    console.log(`For document: "${collection[i].title}", the relevancy (high to low) of term:`)

    for (let item of calcData) {
        console.log(`${item.term}: ${item.tf_idf.toFixed(4)}`);
    }

    console.log('\n');
}
