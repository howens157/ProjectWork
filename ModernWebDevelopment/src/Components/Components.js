import Header from "./Common/Header.js"
import HomeModule from "./Home/Home.js";
import StatsModule from "./Stats/Stats.js";
import {
    BrowserRouter as Router,
    Route,
    Switch,
    Redirect
  } from "react-router-dom";

//route between different modules
const Components = () => {
    return (
        <Router>
            <Header />
            <hr />
            <Switch>
                <Route path="/" exact component={HomeModule} />
                <Route path="/stats" component={StatsModule} />
                <Redirect to="/" />
            </Switch>
        </Router>
    )
}

export default Components;