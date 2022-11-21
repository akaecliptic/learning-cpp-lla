export const INSERT_TABLE_VERB: string = `INSERT OR IGNORE INTO table_verb (verb, translation, is_irregular, is_reflexsive) VALUES (?, ?, ?, ?);`;
const INSERT_TABLE_TENSE_TEMPLATE: string = `INSERT INTO table_tense_REPLACESTRING (
    verb,
    yo,
    tu,
    usted,
    nosotros,
    vosotros,
    ustedes,
    vos
) VALUES (?, ?, ?, ?, ?, ?, ?, ?);`;

const map: Map<string, string> = new Map();
map.set( 'presentIndicative',            'present_indicative' );
map.set( 'preteritIndicative',           'preterit_indicative' );
map.set( 'imperfectIndicative',          'imperfect_indicative' );
map.set( 'conditionalIndicative',        'conditional_indicative' );
map.set( 'futureIndicative',             'future_indicative' );
map.set( 'presentSubjunctive',           'present_subjunctive' );
map.set( 'imperfectSubjunctive',         'imperfect_subjunctive' );
map.set( 'futureSubjunctive',            'future_subjunctive' );
map.set( 'imperative',                   'imperative' );
map.set( 'negativeImperative',           'negative_imperative' );
map.set( 'presentContinuous',            'present_continuous' );
map.set( 'preteritContinuous',           'preterit_continuous' );
map.set( 'imperfectContinuous',          'imperfect_continuous' );
map.set( 'conditionalContinuous',        'conditional_continuous' );
map.set( 'futureContinuous',             'future_continuous' );
map.set( 'presentPerfect',               'present_perfect' );
map.set( 'preteritPerfect',              'preterit_perfect' );
map.set( 'pastPerfect',                  'past_perfect' );
map.set( 'conditionalPerfect',           'conditional_perfect' );
map.set( 'futurePerfect',                'future_perfect' );
map.set( 'presentPerfectSubjunctive',    'present_perfect_subjunctive' );
map.set( 'pastPerfectSubjunctive',       'past_perfect_subjunctive' );
map.set( 'futurePerfectSubjunctive',     'future_perfect_subjunctive' );

export const GET_INSERT_TABLE_TENSE = ( tense: string ): string | null => {
    const replacer: string | undefined = map.get(tense);

    if ( replacer === undefined ) return null;

    return INSERT_TABLE_TENSE_TEMPLATE.replace( 'REPLACESTRING', replacer );
};


// OLD INSERT STATEMENT - NOT USED
export const INSERT_TABLE_TENSES: string = `INSERT INTO table_tenses (
    verb,
    presentIndicative,
    preteritIndicative,
    imperfectIndicative,
    conditionalIndicative,
    futureIndicative,
    presentSubjunctive,
    imperfectSubjunctive,
    futureSubjunctive,
    imperative,
    negativeImperative,
    presentContinuous,
    preteritContinuous,
    imperfectContinuous,
    conditionalContinuous,
    futureContinuous,
    presentPerfect,
    preteritPerfect,
    pastPerfect,
    conditionalPerfect,
    futurePerfect,
    presentPerfectSubjunctive,
    pastPerfectSubjunctive,
    futurePerfectSubjunctive
) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);`;

