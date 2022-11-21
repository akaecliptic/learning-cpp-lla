import { join } from "path";

export const APP_DIR: string = join(__dirname, '../../');
export const DATABASE_PATH: string = APP_DIR.concat('../data.db');

export const VERBS_DIR: string = join(APP_DIR, '../processed_verbs/');
