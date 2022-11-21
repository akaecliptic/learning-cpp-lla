interface IConjuction {
    word: string;
    translation: string;
    isIrregular: boolean;
    pronoun: string;
    audioUrl: string;
};

interface IConjuctionBlock {
    tense: string;
    block: IConjuction[];
};

export interface IVerb {
    infinitive: string;
    infinitiveTranslation: string;
    isIrregular: boolean;
    tenses: IConjuctionBlock[];
};
