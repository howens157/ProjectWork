import { Chart as ChartJS, ArcElement, Tooltip, Legend } from 'chart.js';
import { Doughnut } from 'react-chartjs-2';

ChartJS.register(ArcElement, Tooltip, Legend);

const userDoughnut = (props) => {
    //options for how the graph is formatted
    const options = {
        responsive: true,
        plugins: {
          legend: {
            position: 'bottom',
            labels: {
                font: {
                    size: 16
                }
            }
          },
        },
        color: 'rgba(255, 255, 255, 1)'
    };

    //data and settings for data
    const data = {
        //map user stats to a list of topics
        labels: props.userStats.map(x => x.topic),
        datasets: [
            {
            label: '# of Questions Attempted',
            //map user stats to just the number attempted in each category
            data: props.userStats.map(x => x.total),
            backgroundColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
            ],
            borderWidth: 1,
            },
        ],
    };

    return (
        <div className="graph">
           <h2>Topic Breakdown</h2>
           <Doughnut data={data} options={options}/>
        </div>
    );
}
export default userDoughnut;