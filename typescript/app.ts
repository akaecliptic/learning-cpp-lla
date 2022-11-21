import { IQueryVerb, IQueryTense } from "@auxil/shapes/sqlite";
import { IVerb } from "@auxil/shapes/verbs";
import { CREATE_VIEW, range } from "@auxil/statements/creates";
import { createTables, createViews, insertTenses, insertVerbs } from "dao";
import { getAllVerbFiles, readFileAsJson } from "io";

/*
    This is a very crass way to populate a database needed for the main focus of this project; The C++ application.

    Originally, this included a web scraper, which I used to 'liberate' this data... It was only really meant to run once and poorly done. So, I removed it.
    This section takes the processed webpages (also removed the processing code) and formats them so they can be easily persisted in relational databases.

    This was revisited and cleaned up a little. The original database design was clunky, rushed and became a problem to work with for the first implementation of the C++ application.
    That version is still present and can be seen in cpp/database.db

    -

    After finishing the refactor, this database is still clunky. Sad... Oh well.
*/

const runSQL = (): void => {
    createTables();

    const files: string[] = getAllVerbFiles();
    const queryVerbs: IQueryVerb[] = []; 
    const queryTense: [string, IQueryTense][] = [];

    files.forEach( file => {
        const json: IVerb = readFileAsJson(file) as IVerb;

        //Pulling top level info from processed verb file
        const verb: IQueryVerb = {
            verb: json.infinitive,
            translation: json.infinitiveTranslation.replace(/\,\s+/g, '|'),
            is_irregular: (json.isIrregular) ? 1 : 0,
            is_reflexsive: 0
        };

        //Going into the tenses array and pulling out relevant data from blocks
        json.tenses.forEach( conj => {
            const pair: [string, IQueryTense] = [ 
                conj.tense, 
                { 
                    verb: json.infinitive,
                    yo: conj.block[0].word.replace(/\,/g, '|'),
                    tu: conj.block[1].word.replace(/\,/g, '|'),
                    usted: conj.block[2].word.replace(/\,/g, '|'),
                    nosotros: conj.block[3].word.replace(/\,/g, '|'),
                    vosotros: conj.block[4].word.replace(/\,/g, '|'),
                    ustedes: conj.block[5].word.replace(/\,/g, '|'),
                    vos: conj.block[6].word.replace(/\,/g, '|')           
                }   
            ];
            queryTense.push(pair);
        });
        
        queryVerbs.push(verb);
    });

    insertVerbs(...queryVerbs);
    insertTenses(...queryTense);
};

runSQL();

for (let i = 0; i < 5; i++) {
    const view: string = CREATE_VIEW(i as range);
    createViews(view);
};
