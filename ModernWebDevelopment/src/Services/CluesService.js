import * as Env from "./environments";
import Parse from "parse";

Parse.initialize(Env.APPLICATION_ID, Env.JAVASCRIPT_KEY);
Parse.serverURL = Env.SERVER_URL;

// Get list of topics
export const GetAllTopics = async () => {
  const Topic = Parse.Object.extend("Topics");
  const query = new Parse.Query(Topic);
  return query.find().then((results) => {
    return results.map((e) => e.get("Name"));
  });
};

// Get category given topic name
export const GetCategory = async (topicName) => {
  // Get topic first
  const Topic = Parse.Object.extend("Topics");
  const topicQuery = new Parse.Query(Topic);
  topicQuery.equalTo("Name", topicName);
  return topicQuery.find().then((topicResult) => {
    const Category = Parse.Object.extend("Category");
    // Pointer for topic to get category
    const topicPointer = {
        __type: 'Pointer',
        className: 'Topics',
        objectId: topicResult[0] ? topicResult[0].id : ""
    }
    const catQuery = new Parse.Query(Category);
    catQuery.equalTo("Topic", topicPointer);
    return catQuery.find().then((result) => {
        return {airDate: result[0].get('AirDate'), catName: result[0].get('Name'), clues: result[0].get('Clues').map(e => e.answer)};
    });
  });
};

// Get user stats given user ID
/*
    Usage:
    GetUserStats(userID).then((results) => {
        console.log(results);
    });
*/
export const GetUserStats = async (userID) => {
    // Use Parse.User.current() later
    const query = new Parse.Query(Parse.User);
    return query.get(userID).then((results) => {
        return results.get('Stats');
    });
}