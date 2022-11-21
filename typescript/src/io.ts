import { VERBS_DIR } from "@config/constants";
import { readFileSync, readdirSync } from "fs";

export const getAllVerbFiles = (): string[] => {
    return readdirSync(VERBS_DIR, { encoding: 'utf-8' }).map( file => VERBS_DIR.concat(file) );
};

export const readFile = ( path: string ): string => {
    return readFileSync(path, { encoding: 'utf-8' });
};

export const readFileAsJson = ( path: string ): object => {
    return JSON.parse(readFileSync(path, { encoding: 'utf-8' }));
};
