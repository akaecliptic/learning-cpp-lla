export type sbool = 0 | 1;

export interface IQueryVerb {
    verb: string;
    translation: string;
    is_irregular: sbool;
    is_reflexsive: sbool;
};

export interface IQueryTense {
    verb: string;
    yo: string;
    tu: string;
    usted: string;
    nosotros: string;
    vosotros: string;
    ustedes: string;
    vos: string;
};
