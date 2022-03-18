const Clue = (props) => {
    // Ternary to display nothing when air date isn't defined yet
    return (
        <div className="clue">
            <h2>Category name: {props.catName} Air date: {props.airDate ? props.airDate.toDateString() : ""} </h2>
            <br />
            <h2>
            Clue: {props.clue}
            </h2>
        </div>
    );
}
export default Clue;