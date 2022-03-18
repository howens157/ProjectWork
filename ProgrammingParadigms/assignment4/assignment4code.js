/* This dataset is based on research by Stanley Coren, a professor of canine psychology at the University of British Columbia. When Coren first published his book in 1994, there was a high degree of dispute of his analysis, though over time his work has been largely accepted.

Data Dictionary
	  breed:
    category:
    comment:
    obey: probability that the breed obeys the first command (figure is lower bound)
    reps_lower: lower limit of repetitions to understand new commands
    reps_upper: upper limit of repetitions to understand new commands */

// You can import the entire list from here if you want to work with a larger dataset:
//

let dogList = [
  ["Affenpinscher", "toy", "Above Average Working Dogs", "0.7", "16", "25"],
  ["Airedale Terrier", "terrier", "Above Average Working Dogs", "0.7", "16", "25"],
  ["Akita", "working", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Alaskan Malamute", "working", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["American Foxhound", "hound", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["American Staffordshire Terrier", "terrier", "Above Average Working Dogs", "0.7", "16", "25"],
  ["American Water Spaniel", "sporting", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Australian Cattle Dog", "herding", "Brightest Dogs", "0.95", "1", "4"],
  ["Australian Shepherd", "herding", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Australian Terrier", "terrier", "Above Average Working Dogs", "0.7", "16", "25"],
  ["Bearded Collie", "herding", "Above Average Working Dogs", "0.7", "16", "25"],
  ["Bedlington Terrier", "terrier", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Belgian Malinois", "herding", "Excellent Working Dogs", "0.85", "5", "15"],
  ["Belgian Sheepdog", "herding", "Excellent Working Dogs", "0.85", "5", "15"],
  ["Bernese Mountain Dog", "working", "Excellent Working Dogs", "0.85", "5", "15"],
  ["Bichon Frise", "nonSporting", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Black and Tan Coonhound", "hound", "Average Working/Obedience Intelligence", "0.5", "26", "40"],
  ["Border Collie", "herding", "Brightest Dogs", "0.95", "1", "4"],
  ["Border Terrier", "terrier", "Above Average Working Dogs", "0.7", "16", "25"],
  ["Boston Terrier", "nonSporting", "Average Working/Obedience Intelligence", "0.5", "26", "40"]
]

let convert = {};

class Dog {
    // Create your dog class here
    constructor(breed, category, comment, obey, reps_lower, reps_upper) {
        this.breed = breed;
        this.category = category;
        this.comment = comment;
        this.obey = obey;
        this.reps_lower = reps_lower;
        this.reps_upper = reps_upper;
    }
}

let dogs = dogList.map(dog => new Dog(dog[0], dog[1], dog[2], dog[3], dog[4], dog[5]));


// Q1: How many terriers have an obey factor greater or equal to 0.7?
function Q1() {
    let obedientTerriers = dogs.filter(dog => dog.category === "terrier").filter(dog => parseFloat(dog.obey) >= 0.7).length;
    return obedientTerriers;
}
let obedientTerriers = Q1();
console.log(`${obedientTerriers} terriers have an obey factory greater or equal to 0.7`);

// Q2: List all the dog BREEDS for whom the average range between lower and upper responses is greater than 10
function Q2() {
    let largeRangeBreeds = dogs.filter(dog => parseInt(dog.reps_upper) - parseInt(dog.reps_lower) > 10).map(dog => dog.breed);
    return largeRangeBreeds;
}
let largeRangeBreeds = Q2();
console.log("The following dogs have response ranges greater than 10");
console.log(largeRangeBreeds);

// Q3: Count the number of dogs by category using a reduce function that leverages a Class method.
function Q3() {
    class catCounterClass {
        constructor() {
            this.cats = [];
        }
        
        categoryCounter(current) {
            for (const cat of this.cats) {
                if(cat[0] === current) {
                    cat[1]++;
                    return;
                }
            }
            this.cats.push([current, 1]);
        }
    }

    categoryCounts = new catCounterClass();

    let dogCats1 = dogs.map(dog => dog.category).reduce((prev, current) => categoryCounts.categoryCounter(current), 0);
    return categoryCounts.cats;
}

let catCounts1 = Q3(); 
console.log("Category counts using class method: ");
console.log(catCounts1);

// Q4: Count the number of dogs by category using a reduce function that leverages a Java Closure function to count the categories

function Q4() {
    function catCounterClosure() {
        let cats = [];

        this.getCats = function() {
            return cats;
        }

        this.categoryCounter = function(current) {
            for (const cat of cats) {
                if(cat[0] === current) {
                    cat[1]++;
                    return;
                }
            }
            cats.push([current, 1]);
            return;
        }
    }

    closureCounts = new catCounterClosure();

    let dogCats2 = dogs.map(dog => dog.category).reduce((prev, current) => closureCounts.categoryCounter(current), 0);
    return closureCounts.getCats();
}

let catCounts2 = Q4();
console.log("Category counts using closure function: ");
console.log(catCounts2);
