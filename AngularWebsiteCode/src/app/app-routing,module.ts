import { NgModule }             from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { DailyTrendComponent }   from './daily-trend/daily-trend.component';
import { MonthlyTrendComponent }      from './monthly-trend/monthly-trend.component';
import { HomePageComponent }      from './home-page/home-page.component';


const routes: Routes = [
  { path: '', redirectTo: '/home-page', pathMatch: 'full' },
  { path: 'dailytrend', component: DailyTrendComponent },
  { path: 'monthlytrend', component: MonthlyTrendComponent },
  
];

@NgModule({
  imports: [ RouterModule.forRoot(routes) ],
  exports: [ RouterModule ]
})
export class AppRoutingModule {}


/*
Copyright 2017-2018 Google Inc. All Rights Reserved.
Use of this source code is governed by an MIT-style license that
can be found in the LICENSE file at http://angular.io/license
*/