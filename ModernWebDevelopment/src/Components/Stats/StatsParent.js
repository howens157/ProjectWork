import { useEffect, useState } from "react";
import UserBar from "./UserBar.js"
import UserDoughnut from "./UserDoughnut.js"
import { GetUserStats } from "../../Services/CluesService";

export default function StatsParent() {
    //example userID
    let myUserID = 'CMnzc2Myuq'
    const [userData, setUserData] = useState([]);

    // get the users stats asynchronously
    useEffect(() => {
        GetUserStats(myUserID).then((results) => {
            setUserData(results);
        });
    }, [myUserID]);

    return (
        <>
            <h1 className="statsHead">User Statistics</h1>
            <div className="content">
                <UserBar userStats={userData}/>
                <UserDoughnut userStats={userData}/>
            </div>
        </>
    );
};