const Topics = (props) => {
    // Ternary to show loading text when topics is undefined
    return (
        <div className="topic">
            {
                props.topics ? props.topics.map((e, i) => {
                    // Ternary to set style of button depending on what the current topic is
                    return (
                    <button className={props.currentTopic === e ? "activeTopic" : "inactiveTopic"} key={i} onClick={props.onTopicChange}>
                        {e}
                    </button>
                    );
                }) : <h1 style={{ textAlign: "center" }}>Loading topics...</h1>
            }
        </div>
    );
}
export default Topics;