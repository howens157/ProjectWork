import React from 'react';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';
import { Bar } from 'react-chartjs-2';

ChartJS.register(
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

const userBar = (props) => {
    //options for how the graphs is formatted
    const options = {
        responsive: true,
        plugins: {
          legend: {
            position: 'bottom',
            labels: {
                font: {
                    size: 16,
                }
            }
          },
        },
        color: 'rgba(255, 255, 255, 1)',
        scales: {
            x: {
                ticks: {
                    color: "white"
                },
                grid: {
                    display: false,
                    color: "white"
                }
            },
            y: {
                ticks: {
                    color: "white"
                },
                grid: {
                    display: true,
                    color: "white"
                }
            },
        }
    };
    
    //map the userStats array to a list of topics to graph
    const labels = props.userStats.map(x => x.topic);
      
    const data = {
        labels,
        datasets: [
          {
            label: 'Accuracy Per Topic',
            //map the userStats to accuracy percentages
            data: props.userStats.map(x => x.correct/x.total),
            backgroundColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
            ],
            color: 'rgba(255, 255, 255, 1)',
          },
        ],
    };
    
    return (
        <div className="graph">
           <h2>Accuracy Per Topic</h2>
           <Bar options={options} data={data} />
        </div>
    );
}
export default userBar;