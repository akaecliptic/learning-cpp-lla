import { IQueryVerb, IQueryTense } from "@auxil/shapes/sqlite";
import { GET_TABLE_TENSE, CREATE_TABLE_VERB } from "@auxil/statements/creates";
import { GET_INSERT_TABLE_TENSE, INSERT_TABLE_VERB } from "@auxil/statements/inserts";
import { DATABASE_PATH } from "@config/constants";
import SQLite3, { sqlite3, Statement } from "sqlite3";

const sqlite: sqlite3 = SQLite3.verbose();
const database: SQLite3.Database = new sqlite.Database(DATABASE_PATH);

export const createTables = (): void => {
    database.serialize( () => {
        database.run(CREATE_TABLE_VERB);
        GET_TABLE_TENSE().forEach( create => database.run(create) );
    });
};

export const insertVerbs = ( ...units: IQueryVerb[] ): void => {
    const statement: Statement = database.prepare(INSERT_TABLE_VERB);
    units.forEach( unit => {
        statement.run([unit.verb, unit.translation, unit.is_irregular, unit.is_reflexsive]);
    });
    statement.finalize();
};

export const insertTenses = ( ...pairs: [string, IQueryTense][]  ): void => {
    pairs.forEach( pair => {
        const insert: string | null = GET_INSERT_TABLE_TENSE(pair[0]);
        
        if ( insert === null ) return;
        
        const statement: Statement = database.prepare(insert);
        statement.run([
            pair[1].verb,
            pair[1].yo,
            pair[1].tu,
            pair[1].usted,
            pair[1].nosotros,
            pair[1].vosotros,
            pair[1].ustedes,
            pair[1].vos
        ]);
        statement.finalize();
    });
};

export const createViews = ( view: string ): void => {
    database.exec(view);
};
