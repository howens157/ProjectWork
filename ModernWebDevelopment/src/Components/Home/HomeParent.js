import { useEffect, useState } from "react";

import Topics from "./Topics.js";
import Clue from "./Clue.js";
import Answer from "./Answer.js";

import { GetAllTopics, GetCategory } from "../../Services/CluesService";

export default function HomeParent() {
    const [clueData, setClues] = useState({
        topic: "History",
        clues: [],
        clueIndex: 0,
        airDate: "",
        catName: "",
        topicList: []
    });

    // Only retrieve topic list at beginning
    useEffect(() => {
        GetAllTopics().then((results) => {
            setClues(prevClues => {
                return {...prevClues, topicList: results};
            });
        });
    }, []);

    // Update clue whenever topic is changed
    useEffect(() => {
        GetCategory(clueData.topic).then((results) => {
            setClues(prevClues => {
                return {
                    ...prevClues,
                    airDate: results.airDate,
                    catName: results.catName,
                    clues: results.clues,
                    clueIndex: 0
                };
            });
        });
    }, [clueData.topic]);

    function switchTopic(e) {
        let topic = e.target.innerHTML;
        if (clueData.topic !== topic) {
            setClues(prevClues => {
                return {
                    ...prevClues,
                    topic: topic
                }
            });
        }
    }


    return (
        <>
            <Topics topics={clueData.topicList} currentTopic={clueData.topic} onTopicChange={switchTopic} />
            <div className="content">
                <Clue catName={clueData.catName} airDate={clueData.airDate} clue={clueData.clues[clueData.clueIndex]} />
                <Answer />
            </div>
        </>
    );
};