export const CREATE_TABLE_VERB: string = `CREATE TABLE IF NOT EXISTS table_verb ( 
    verb TEXT PRIMARY KEY,
    translation TEXT NOT NULL,
    is_irregular INTEGER DEFAULT 0,
    is_reflexsive INTEGER DEFAULT 0
);`;

const CREATE_TABLE_TENSE_TEMPLATE: string = `CREATE TABLE IF NOT EXISTS table_tense_REPLACESTRING (
    verb TEXT,
    yo TEXT,
    tu TEXT,
    usted TEXT,
    nosotros TEXT,
    vosotros TEXT,
    ustedes TEXT,
    vos TEXT,
    FOREIGN KEY (verb) REFERENCES table_verb (verb)
);`;

export const GET_TABLE_TENSE = (): string[] => {
    const replacers: string[] = [
        'present_indicative',
        'preterit_indicative',
        'imperfect_indicative',
        'conditional_indicative',
        'future_indicative',
        'present_subjunctive',
        'imperfect_subjunctive',
        'future_subjunctive',
        'imperative',
        'negative_imperative',
        'present_continuous',
        'preterit_continuous',
        'imperfect_continuous',
        'conditional_continuous',
        'future_continuous',
        'present_perfect',
        'preterit_perfect',
        'past_perfect',
        'conditional_perfect',
        'future_perfect',
        'present_perfect_subjunctive',
        'past_perfect_subjunctive',
        'future_perfect_subjunctive' 
    ];

    return replacers.map( replacer => CREATE_TABLE_TENSE_TEMPLATE.replace('REPLACESTRING', replacer) );
};

//!Please avert your eyes from the code below... It is 5am, I'm very tired and really lazy...

const TEMPLATE_VIEW_BASE: string = 'CREATE VIEW IF NOT EXISTS view_ALIAS AS SELECT verb.*, ';
const TEMPLATE_JOIN_BASE: string = 'FROM table_verb verb ';

const TEMPLATE_SELECT: string = 'ALIAS.yo, ALIAS.tu, ALIAS.usted, ALIAS.nosotros, ALIAS.vosotros, ALIAS.ustedes, ALIAS.vos';
const TEMPLATE_INNER_JOIN: string = 'LEFT JOIN table_tense_ALIAS ALIAS ON verb.verb = ALIAS.verb';

export type range = 0 | 1 | 2 | 3 | 4;

export const CREATE_VIEW = ( tense: range ): string => {
    const replacers: string[][] = [
        [
            'present_indicative',
            'preterit_indicative',
            'imperfect_indicative',
            'conditional_indicative',
            'future_indicative'
        ],
        [
            'present_subjunctive',
            'imperfect_subjunctive',
            'future_subjunctive'
        ],
        [
            'imperative',
            'negative_imperative'
        ],
        [
            'present_continuous',
            'preterit_continuous',
            'imperfect_continuous',
            'conditional_continuous',
            'future_continuous'
        ],
        [
        'present_perfect',
        'preterit_perfect',
        'past_perfect',
        'conditional_perfect',
        'future_perfect',
        'present_perfect_subjunctive',
        'past_perfect_subjunctive',
        'future_perfect_subjunctive' 
        ]
    ];

    const names: string[] = [ 'base', 'subjunctive', 'imperative', 'continuous', 'perfect' ];

    let view: string = '';

    view += TEMPLATE_VIEW_BASE.replace('ALIAS', names[tense]);
    replacers[tense].forEach( (replacer, index) => {
        view += 
            (index == replacers[tense].length - 1) ? 
            TEMPLATE_SELECT.replace(/ALIAS/g, replacer) + ' ': 
            TEMPLATE_SELECT.replace(/ALIAS/g, replacer) + ',';
        
    });
    view += TEMPLATE_JOIN_BASE
    replacers[tense].forEach( (replacer, index) => {
        view += 
            (index == replacers[tense].length - 1) ? 
            TEMPLATE_INNER_JOIN.replace(/ALIAS/g, replacer) + ';': 
            TEMPLATE_INNER_JOIN.replace(/ALIAS/g, replacer) + ' ';
        
    });

    return view;
};

// OLD CREATE STATEMENT - NOT USED
export const CREATE_TABLE_TENSES: string = `CREATE TABLE IF NOT EXISTS table_tenses (
    verb TEXT,
    presentIndicative TEXT,
    preteritIndicative TEXT,
    imperfectIndicative TEXT,
    conditionalIndicative TEXT,
    futureIndicative TEXT,
    presentSubjunctive TEXT,
    imperfectSubjunctive TEXT,
    futureSubjunctive TEXT,
    imperative TEXT,
    negativeImperative TEXT,
    presentContinuous TEXT,
    preteritContinuous TEXT,
    imperfectContinuous TEXT,
    conditionalContinuous TEXT,
    futureContinuous TEXT,
    presentPerfect TEXT,
    preteritPerfect TEXT,
    pastPerfect TEXT,
    conditionalPerfect TEXT,
    futurePerfect TEXT,
    presentPerfectSubjunctive TEXT,
    pastPerfectSubjunctive TEXT,
    futurePerfectSubjunctive TEXT,
    FOREIGN KEY (verb) REFERENCES table_verbs (verb)
)`;
